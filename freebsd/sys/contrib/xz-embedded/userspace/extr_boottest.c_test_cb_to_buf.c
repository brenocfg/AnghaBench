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
 int decompress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/  fill ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  in ; 
 int /*<<< orphan*/  out ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void test_cb_to_buf(void)
{
	int in_used;
	int ret;
	ret = decompress(in, 0, &fill, NULL, out, &in_used, &error);
	/* fwrite(out, 1, FIXME, stdout); */
	fprintf(stderr, "ret = %d; in_used = %d\n", ret, in_used);
}