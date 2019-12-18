#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* manpath; scalar_t__ equal; int /*<<< orphan*/ * arch; } ;
struct req {TYPE_1__ q; int /*<<< orphan*/ * p; scalar_t__ isquery; } ;
struct manpage {char* file; int /*<<< orphan*/  output; int /*<<< orphan*/  names; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOCUS_NONE ; 
 int /*<<< orphan*/  FOCUS_QUERY ; 
 int /*<<< orphan*/  html_print (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_error_internal () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  resp_begin_html (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  resp_end_html () ; 
 int /*<<< orphan*/  resp_searchform (struct req const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resp_show (struct req const*,char*) ; 
 char* scriptname ; 
 int* sec_prios ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcspn (char const*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ validate_filename (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*,char*) ; 

__attribute__((used)) static void
pg_searchres(const struct req *req, struct manpage *r, size_t sz)
{
	char		*arch, *archend;
	const char	*sec;
	size_t		 i, iuse;
	int		 archprio, archpriouse;
	int		 prio, priouse;

	for (i = 0; i < sz; i++) {
		if (validate_filename(r[i].file))
			continue;
		warnx("invalid filename %s in %s database",
		    r[i].file, req->q.manpath);
		pg_error_internal();
		return;
	}

	if (req->isquery && sz == 1) {
		/*
		 * If we have just one result, then jump there now
		 * without any delay.
		 */
		printf("Status: 303 See Other\r\n"
		    "Location: /");
		if (*scriptname != '\0')
			printf("%s/", scriptname);
		if (strcmp(req->q.manpath, req->p[0]))
			printf("%s/", req->q.manpath);
		printf("%s\r\n"
		    "Content-Type: text/html; charset=utf-8\r\n\r\n",
		    r[0].file);
		return;
	}

	/*
	 * In man(1) mode, show one of the pages
	 * even if more than one is found.
	 */

	iuse = 0;
	if (req->q.equal || sz == 1) {
		priouse = 20;
		archpriouse = 3;
		for (i = 0; i < sz; i++) {
			sec = r[i].file;
			sec += strcspn(sec, "123456789");
			if (sec[0] == '\0')
				continue;
			prio = sec_prios[sec[0] - '1'];
			if (sec[1] != '/')
				prio += 10;
			if (req->q.arch == NULL) {
				archprio =
				    ((arch = strchr(sec + 1, '/'))
					== NULL) ? 3 :
				    ((archend = strchr(arch + 1, '/'))
					== NULL) ? 0 :
				    strncmp(arch, "amd64/",
					archend - arch) ? 2 : 1;
				if (archprio < archpriouse) {
					archpriouse = archprio;
					priouse = prio;
					iuse = i;
					continue;
				}
				if (archprio > archpriouse)
					continue;
			}
			if (prio >= priouse)
				continue;
			priouse = prio;
			iuse = i;
		}
		resp_begin_html(200, NULL, r[iuse].file);
	} else
		resp_begin_html(200, NULL, NULL);

	resp_searchform(req,
	    req->q.equal || sz == 1 ? FOCUS_NONE : FOCUS_QUERY);

	if (sz > 1) {
		puts("<table class=\"results\">");
		for (i = 0; i < sz; i++) {
			printf("  <tr>\n"
			       "    <td>"
			       "<a class=\"Xr\" href=\"/");
			if (*scriptname != '\0')
				printf("%s/", scriptname);
			if (strcmp(req->q.manpath, req->p[0]))
				printf("%s/", req->q.manpath);
			printf("%s\">", r[i].file);
			html_print(r[i].names);
			printf("</a></td>\n"
			       "    <td><span class=\"Nd\">");
			html_print(r[i].output);
			puts("</span></td>\n"
			     "  </tr>");
		}
		puts("</table>");
	}

	if (req->q.equal || sz == 1) {
		puts("<hr>");
		resp_show(req, r[iuse].file);
	}

	resp_end_html();
}