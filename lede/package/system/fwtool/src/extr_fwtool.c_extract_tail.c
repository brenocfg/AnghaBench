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
struct data_buf {int cur_len; scalar_t__ cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int) ; 
 int /*<<< orphan*/  remove_tail (struct data_buf*,int) ; 

__attribute__((used)) static int
extract_tail(struct data_buf *dbuf, void *dest, int len)
{
	int cur_len = dbuf->cur_len;

	if (!dbuf->cur)
		return 1;

	if (cur_len >= len)
		cur_len = len;

	memcpy(dest + (len - cur_len), dbuf->cur + dbuf->cur_len - cur_len, cur_len);
	remove_tail(dbuf, cur_len);

	cur_len = len - cur_len;
	if (cur_len && !dbuf->cur)
		return 1;

	memcpy(dest, dbuf->cur + dbuf->cur_len - cur_len, cur_len);
	remove_tail(dbuf, cur_len);

	return 0;
}