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
struct TYPE_2__ {char* manpath; char* arch; char const* sec; } ;
struct req {TYPE_1__ q; int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 int /*<<< orphan*/  http_encode (char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 char* scriptname ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pg_redirect(const struct req *req, const char *name)
{
	printf("Status: 303 See Other\r\n"
	    "Location: /");
	if (*scriptname != '\0')
		printf("%s/", scriptname);
	if (strcmp(req->q.manpath, req->p[0]))
		printf("%s/", req->q.manpath);
	if (req->q.arch != NULL)
		printf("%s/", req->q.arch);
	http_encode(name);
	if (req->q.sec != NULL) {
		putchar('.');
		http_encode(req->q.sec);
	}
	printf("\r\nContent-Type: text/html; charset=utf-8\r\n\r\n");
}