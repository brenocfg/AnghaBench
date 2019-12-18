#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct val_anchors {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_5__ {char const** gl_pathv; scalar_t__ gl_pathc; } ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  g ;

/* Variables and functions */
 int GLOB_ABORTED ; 
 int GLOB_BRACE ; 
 int GLOB_ERR ; 
 int GLOB_NOMATCH ; 
 int GLOB_NOSORT ; 
 int GLOB_NOSPACE ; 
 int GLOB_TILDE ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int anchor_read_bind_file (struct val_anchors*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  errno ; 
 int glob (char const*,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int /*<<< orphan*/  log_err (char*,char const*,...) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int
anchor_read_bind_file_wild(struct val_anchors* anchors, sldns_buffer* buffer,
	const char* pat)
{
#ifdef HAVE_GLOB
	glob_t g;
	size_t i;
	int r, flags;
	if(!strchr(pat, '*') && !strchr(pat, '?') && !strchr(pat, '[') && 
		!strchr(pat, '{') && !strchr(pat, '~')) {
		return anchor_read_bind_file(anchors, buffer, pat);
	}
	verbose(VERB_QUERY, "wildcard found, processing %s", pat);
	flags = 0 
#ifdef GLOB_ERR
		| GLOB_ERR
#endif
#ifdef GLOB_NOSORT
		| GLOB_NOSORT
#endif
#ifdef GLOB_BRACE
		| GLOB_BRACE
#endif
#ifdef GLOB_TILDE
		| GLOB_TILDE
#endif
	;
	memset(&g, 0, sizeof(g));
	r = glob(pat, flags, NULL, &g);
	if(r) {
		/* some error */
		if(r == GLOB_NOMATCH) {
			verbose(VERB_QUERY, "trusted-keys-file: "
				"no matches for %s", pat);
			return 1;
		} else if(r == GLOB_NOSPACE) {
			log_err("wildcard trusted-keys-file %s: "
				"pattern out of memory", pat);
		} else if(r == GLOB_ABORTED) {
			log_err("wildcard trusted-keys-file %s: expansion "
				"aborted (%s)", pat, strerror(errno));
		} else {
			log_err("wildcard trusted-keys-file %s: expansion "
				"failed (%s)", pat, strerror(errno));
		}
		/* ignore globs that yield no files */
		return 1; 
	}
	/* process files found, if any */
	for(i=0; i<(size_t)g.gl_pathc; i++) {
		if(!anchor_read_bind_file(anchors, buffer, g.gl_pathv[i])) {
			log_err("error reading wildcard "
				"trusted-keys-file: %s", g.gl_pathv[i]);
			globfree(&g);
			return 0;
		}
	}
	globfree(&g);
	return 1;
#else /* not HAVE_GLOB */
	return anchor_read_bind_file(anchors, buffer, pat);
#endif /* HAVE_GLOB */
}