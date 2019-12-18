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
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  una; int /*<<< orphan*/  sn; int /*<<< orphan*/  ts; scalar_t__ wnd; scalar_t__ frg; scalar_t__ cmd; int /*<<< orphan*/  conv; } ;
typedef  int /*<<< orphan*/  IUINT8 ;
typedef  int /*<<< orphan*/  IUINT16 ;
typedef  TYPE_1__ IKCPSEG ;

/* Variables and functions */
 char* ikcp_encode16u (char*,int /*<<< orphan*/ ) ; 
 char* ikcp_encode32u (char*,int /*<<< orphan*/ ) ; 
 char* ikcp_encode8u (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *ikcp_encode_seg(char *ptr, const IKCPSEG *seg)
{
	ptr = ikcp_encode32u(ptr, seg->conv);
	ptr = ikcp_encode8u(ptr, (IUINT8)seg->cmd);
	ptr = ikcp_encode8u(ptr, (IUINT8)seg->frg);
	ptr = ikcp_encode16u(ptr, (IUINT16)seg->wnd);
	ptr = ikcp_encode32u(ptr, seg->ts);
	ptr = ikcp_encode32u(ptr, seg->sn);
	ptr = ikcp_encode32u(ptr, seg->una);
	ptr = ikcp_encode32u(ptr, seg->len);
	return ptr;
}