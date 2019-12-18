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
typedef  int /*<<< orphan*/  uint8_t ;
struct val_anchors {int dummy; } ;
struct trust_anchor {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  autr_assemble (struct trust_anchor*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ handle_origin (char*,int /*<<< orphan*/ **,size_t*) ; 
 struct trust_anchor* load_trustanchor (struct val_anchors*,char*,char const*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ **,size_t*,int*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,char const*,...) ; 
 int /*<<< orphan*/  log_warn (char*,char const*) ; 
 int parse_var_line (char*,struct val_anchors*,struct trust_anchor**) ; 
 int read_multiline (char*,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  str_contains_data (char*,char) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char const*) ; 

int autr_read_file(struct val_anchors* anchors, const char* nm)
{
        /* the file descriptor */
        FILE* fd;
        /* keep track of line numbers */
        int line_nr = 0;
        /* single line */
        char line[10240];
	/* trust point being read */
	struct trust_anchor *tp = NULL, *tp2;
	int r;
	/* for $ORIGIN parsing */
	uint8_t *origin=NULL, *prev=NULL;
	size_t origin_len=0, prev_len=0;

        if (!(fd = fopen(nm, "r"))) {
                log_err("unable to open %s for reading: %s", 
			nm, strerror(errno));
                return 0;
        }
        verbose(VERB_ALGO, "reading autotrust anchor file %s", nm);
        while ( (r=read_multiline(line, sizeof(line), fd, &line_nr)) != 0) {
		if(r == -1 || (r = parse_var_line(line, anchors, &tp)) == -1) {
			log_err("could not parse auto-trust-anchor-file "
				"%s line %d", nm, line_nr);
			fclose(fd);
			free(origin);
			free(prev);
			return 0;
		} else if(r == 1) {
			continue;
		} else if(r == 2) {
			log_warn("trust anchor %s has been revoked", nm);
			fclose(fd);
			free(origin);
			free(prev);
			return 1;
		}
        	if (!str_contains_data(line, ';'))
                	continue; /* empty lines allowed */
 		if(handle_origin(line, &origin, &origin_len))
			continue;
		r = 0;
                if(!(tp2=load_trustanchor(anchors, line, nm, origin,
			origin_len, &prev, &prev_len, &r))) {
			if(!r) log_err("failed to load trust anchor from %s "
				"at line %i, skipping", nm, line_nr);
                        /* try to do the rest */
			continue;
                }
		if(tp && tp != tp2) {
			log_err("file %s has mismatching data inside: "
				"the file may only contain keys for one name, "
				"remove keys for other domain names", nm);
        		fclose(fd);
			free(origin);
			free(prev);
			return 0;
		}
		tp = tp2;
        }
        fclose(fd);
	free(origin);
	free(prev);
	if(!tp) {
		log_err("failed to read %s", nm);
		return 0;
	}

	/* now assemble the data into DNSKEY and DS packed rrsets */
	lock_basic_lock(&tp->lock);
	if(!autr_assemble(tp)) {
		lock_basic_unlock(&tp->lock);
		log_err("malloc failure assembling %s", nm);
		return 0;
	}
	lock_basic_unlock(&tp->lock);
	return 1;
}