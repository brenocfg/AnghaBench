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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static int is_file(const char *url)
{
	struct stat buf;
	if (stat(url, &buf))
		return 0;
	return S_ISREG(buf.st_mode);
}