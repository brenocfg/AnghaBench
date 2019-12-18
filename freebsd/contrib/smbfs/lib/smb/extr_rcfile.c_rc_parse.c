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
struct rcsection {int dummy; } ;
struct rckey {void* rk_value; } ;
struct rcfile {char* rf_name; int /*<<< orphan*/ * rf_f; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (int) ; 
 struct rcsection* rc_addsect (struct rcfile*,char*) ; 
 struct rckey* rc_sect_addkey (struct rcsection*,char*,int /*<<< orphan*/ *) ; 
 int stGetKey ; 
 int stGetValue ; 
 int stHeader ; 
 int stNewLine ; 
 int stSkipToEOL ; 
 int /*<<< orphan*/  stderr ; 
 void* strdup (char*) ; 

__attribute__((used)) static void
rc_parse(struct rcfile *rcp) 
{
	FILE *f = rcp->rf_f;
	int state = stNewLine, c;
	struct rcsection *rsp = NULL;
	struct rckey *rkp = NULL;
	char buf[2048];
	char *next = buf, *last = &buf[sizeof(buf)-1];

	while ((c = getc (f)) != EOF) {
		if (c == '\r')
			continue;
		if (state == stNewLine) {
			next = buf;
			if (isspace(c))
				continue;	/* skip leading junk */
			if (c == '[') {
				state = stHeader;
				rsp = NULL;
				continue;
			}
			if (c == '#' || c == ';') {
				state = stSkipToEOL;
			} else {		/* something meaningfull */
				state = stGetKey;
			}
		}
		if (state == stSkipToEOL || next == last) {/* ignore long lines */
			if (c == '\n'){
				state = stNewLine;
				next = buf;
			}
			continue;
		}
		if (state == stHeader) {
			if (c == ']') {
				*next = 0;
				next = buf;
				rsp = rc_addsect(rcp, buf);
				state = stSkipToEOL;
			} else
				*next++ = c;
			continue;
		}
		if (state == stGetKey) {
			if (c == ' ' || c == '\t')/* side effect: 'key name='*/
				continue;	  /* become 'keyname=' 	     */
			if (c == '\n') {	/* silently ignore ... */
				state = stNewLine;
				continue;
			}
			if (c != '=') {
				*next++ = c;
				continue;
			}
			*next = 0;
			if (rsp == NULL) {
				fprintf(stderr, "Key '%s' defined before section\n", buf);
				state = stSkipToEOL;
				continue;
			}
			rkp = rc_sect_addkey(rsp, buf, NULL);
			next = buf;
			state = stGetValue;
			continue;
		}
		/* only stGetValue left */
		if (state != stGetValue) {
			fprintf(stderr, "Well, I can't parse file '%s'\n",rcp->rf_name);
			state = stSkipToEOL;
		}
		if (c != '\n') {
			*next++ = c;
			continue;
		}
		*next = 0;
		rkp->rk_value = strdup(buf);
		state = stNewLine;
		rkp = NULL;
	} 	/* while */
	if (c == EOF && state == stGetValue) {
		*next = 0;
		rkp->rk_value = strdup(buf);
	}
	return;
}