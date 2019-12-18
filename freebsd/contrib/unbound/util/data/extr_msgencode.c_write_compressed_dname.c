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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct compress_tree_node {int labs; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  PTR_CREATE (int /*<<< orphan*/ ) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  sldns_buffer_write_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_write_u8 (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
write_compressed_dname(sldns_buffer* pkt, uint8_t* dname, int labs,
	struct compress_tree_node* p)
{
	/* compress it */
	int labcopy = labs - p->labs;
	uint8_t lablen;
	uint16_t ptr;

	if(labs == 1) {
		/* write root label */
		if(sldns_buffer_remaining(pkt) < 1)
			return 0;
		sldns_buffer_write_u8(pkt, 0);
		return 1;
	}

	/* copy the first couple of labels */
	while(labcopy--) {
		lablen = *dname++;
		if(sldns_buffer_remaining(pkt) < (size_t)lablen+1)
			return 0;
		sldns_buffer_write_u8(pkt, lablen);
		sldns_buffer_write(pkt, dname, lablen);
		dname += lablen;
	}
	/* insert compression ptr */
	if(sldns_buffer_remaining(pkt) < 2)
		return 0;
	ptr = PTR_CREATE(p->offset);
	sldns_buffer_write_u16(pkt, ptr);
	return 1;
}