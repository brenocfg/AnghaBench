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
struct archive_write {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGICAL_BLOCK_SIZE ; 
 unsigned char RRIP_ER_DSC_SIZE ; 
 unsigned char RRIP_ER_ID_SIZE ; 
 unsigned char RRIP_ER_SIZE ; 
 unsigned char RRIP_ER_SRC_SIZE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrip_descriptor ; 
 int /*<<< orphan*/  rrip_identifier ; 
 int /*<<< orphan*/  rrip_source ; 
 unsigned char* wb_buffptr (struct archive_write*) ; 
 int wb_consume (struct archive_write*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
write_rr_ER(struct archive_write *a)
{
	unsigned char *p;

	p = wb_buffptr(a);

	memset(p, 0, LOGICAL_BLOCK_SIZE);
	p[0] = 'E';
	p[1] = 'R';
	p[3] = 0x01;
	p[2] = RRIP_ER_SIZE;
	p[4] = RRIP_ER_ID_SIZE;
	p[5] = RRIP_ER_DSC_SIZE;
	p[6] = RRIP_ER_SRC_SIZE;
	p[7] = 0x01;
	memcpy(&p[8], rrip_identifier, p[4]);
	memcpy(&p[8+p[4]], rrip_descriptor, p[5]);
	memcpy(&p[8+p[4]+p[5]], rrip_source, p[6]);

	return (wb_consume(a, LOGICAL_BLOCK_SIZE));
}