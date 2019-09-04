#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int fd; int m_buf; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ kurl_t ;

/* Variables and functions */
 int KU_DEF_BUFLEN ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ fill_buffer (TYPE_1__*) ; 
 int /*<<< orphan*/  kurl_close (TYPE_1__*) ; 
 scalar_t__ prepare (TYPE_1__*,int /*<<< orphan*/ ) ; 

kurl_t *kurl_dopen(int fd)
{
	kurl_t *ku;
	ku = (kurl_t*)calloc(1, sizeof(kurl_t));
	ku->fd = fd;
	ku->m_buf = KU_DEF_BUFLEN;
	ku->buf = (uint8_t*)calloc(ku->m_buf, 1);
	if (prepare(ku, 0) < 0 || fill_buffer(ku) <= 0) {
		kurl_close(ku);
		return 0;
	}
	return ku;
}