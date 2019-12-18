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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 size_t fwrite (char const*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
write_out(FILE* out, const char* str, size_t len)
{
	size_t r;
	if(len == 0)
		return 1;
	r = fwrite(str, 1, len, out);
	if(r == 0) {
		log_err("write failed: %s", strerror(errno));
		return 0;
	} else if(r < len) {
		log_err("write failed: too short (disk full?)");
		return 0;
	}
	return 1;
}