#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * _bgzf_file_t ;
struct TYPE_5__ {int /*<<< orphan*/ * fp; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ BGZF ;

/* Variables and functions */
 int /*<<< orphan*/ * _bgzf_dopen (int,char*) ; 
 TYPE_1__* bgzf_read_init () ; 
 TYPE_1__* bgzf_write_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  mode2level (char const*) ; 
 scalar_t__ strchr (char const*,char) ; 

BGZF *bgzf_dopen(int fd, const char *mode)
{
	BGZF *fp = 0;
	if (strchr(mode, 'r') || strchr(mode, 'R')) {
		_bgzf_file_t fpr;
		if ((fpr = _bgzf_dopen(fd, "r")) == 0) return 0;
		fp = bgzf_read_init();
		fp->fp = fpr;
	} else if (strchr(mode, 'w') || strchr(mode, 'W')) {
		FILE *fpw;
		if ((fpw = fdopen(fd, "w")) == 0) return 0;
		fp = bgzf_write_init(mode2level(mode));
		fp->fp = fpw;
	}
	return fp;
}