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
struct evhttp {int dummy; } ;

/* Variables and functions */
 int evhttp_bind_socket (struct evhttp*,char const*,unsigned short) ; 
 struct evhttp* evhttp_new_object () ; 
 int /*<<< orphan*/  mm_free (struct evhttp*) ; 

struct evhttp *
evhttp_start(const char *address, unsigned short port)
{
	struct evhttp *http = NULL;

	http = evhttp_new_object();
	if (http == NULL)
		return (NULL);
	if (evhttp_bind_socket(http, address, port) == -1) {
		mm_free(http);
		return (NULL);
	}

	return (http);
}