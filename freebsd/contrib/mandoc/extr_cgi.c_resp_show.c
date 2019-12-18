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
struct req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  resp_catman (struct req const*,char const*) ; 
 int /*<<< orphan*/  resp_format (struct req const*,char const*) ; 

__attribute__((used)) static void
resp_show(const struct req *req, const char *file)
{

	if ('.' == file[0] && '/' == file[1])
		file += 2;

	if ('c' == *file)
		resp_catman(req, file);
	else
		resp_format(req, file);
}