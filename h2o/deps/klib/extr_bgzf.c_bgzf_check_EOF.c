#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  _bgzf_file_t ;
struct TYPE_3__ {scalar_t__ fp; } ;
typedef  TYPE_1__ BGZF ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  _bgzf_read (scalar_t__,char*,int) ; 
 scalar_t__ _bgzf_seek (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int _bgzf_tell (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 

int bgzf_check_EOF(BGZF *fp)
{
	static uint8_t magic[28] = "\037\213\010\4\0\0\0\0\0\377\6\0\102\103\2\0\033\0\3\0\0\0\0\0\0\0\0\0";
	uint8_t buf[28];
	off_t offset;
	offset = _bgzf_tell((_bgzf_file_t)fp->fp);
	if (_bgzf_seek(fp->fp, -28, SEEK_END) < 0) return 0;
	_bgzf_read(fp->fp, buf, 28);
	_bgzf_seek(fp->fp, offset, SEEK_SET);
	return (memcmp(magic, buf, 28) == 0)? 1 : 0;
}