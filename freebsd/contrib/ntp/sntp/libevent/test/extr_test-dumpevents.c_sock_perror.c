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

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_SOCKET_ERROR () ; 
 char* evutil_socket_error_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
sock_perror(const char *s)
{
#ifdef _WIN32
	const char *err = evutil_socket_error_to_string(EVUTIL_SOCKET_ERROR());
	fprintf(stderr, "%s: %s\n", s, err);
#else
	perror(s);
#endif
}