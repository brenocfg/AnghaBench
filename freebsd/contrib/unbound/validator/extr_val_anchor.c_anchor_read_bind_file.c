#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct val_anchors {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  log_err (char*,char const*,...) ; 
 int /*<<< orphan*/  process_bind_contents (struct val_anchors*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int readkeyword_bindfile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  skip_to_special (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,char) ; 
 scalar_t__ sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int
anchor_read_bind_file(struct val_anchors* anchors, sldns_buffer* buffer,
	const char* fname)
{
	int line_nr = 1;
	FILE* in = fopen(fname, "r");
	int rdlen = 0;
	if(!in) {
		log_err("error opening file %s: %s", fname, strerror(errno));
		return 0;
	}
	verbose(VERB_QUERY, "reading in bind-compat-mode: '%s'", fname);
	/* scan for  trusted-keys  keyword, ignore everything else */
	sldns_buffer_clear(buffer);
	while((rdlen=readkeyword_bindfile(in, buffer, &line_nr, 1)) != 0) {
		if(rdlen != 12 || strncmp((char*)sldns_buffer_begin(buffer),
			"trusted-keys", 12) != 0) {
			sldns_buffer_clear(buffer);
			/* ignore everything but trusted-keys */
			continue;
		}
		if(!skip_to_special(in, buffer, &line_nr, '{')) {
			log_err("error in trusted key: \"%s\"", fname);
			fclose(in);
			return 0;
		}
		/* process contents */
		if(!process_bind_contents(anchors, buffer, &line_nr, in)) {
			log_err("error in trusted key: \"%s\"", fname);
			fclose(in);
			return 0;
		}
		if(!skip_to_special(in, buffer, &line_nr, ';')) {
			log_err("error in trusted key: \"%s\"", fname);
			fclose(in);
			return 0;
		}
		sldns_buffer_clear(buffer);
	}
	fclose(in);
	return 1;
}