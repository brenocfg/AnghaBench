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
struct evkeyvalq {int dummy; } ;

/* Variables and functions */
 char* evhttp_find_header (struct evkeyvalq const*,char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  tt_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tt_want (int) ; 

__attribute__((used)) static int validate_header(
	const struct evkeyvalq* headers,
	const char *key, const char *value)
{
	const char *real_val = evhttp_find_header(headers, key);
	tt_assert(real_val != NULL);
	tt_want(strcmp(real_val, value) == 0);
end:
	return (0);
}