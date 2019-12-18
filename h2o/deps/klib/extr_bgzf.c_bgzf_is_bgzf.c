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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  _bgzf_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  _bgzf_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bgzf_open (char const*,char*) ; 
 int _bgzf_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  g_magic ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int bgzf_is_bgzf(const char *fn)
{
	uint8_t buf[16];
	int n;
	_bgzf_file_t fp;
	if ((fp = _bgzf_open(fn, "r")) == 0) return 0;
	n = _bgzf_read(fp, buf, 16);
	_bgzf_close(fp);
	if (n != 16) return 0;
	return memcmp(g_magic, buf, 16) == 0? 1 : 0;
}