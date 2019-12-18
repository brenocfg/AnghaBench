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
struct isns_req {int ir_usedlen; scalar_t__ ir_buf; } ;
struct isns_hdr {int /*<<< orphan*/  ih_sequence; int /*<<< orphan*/  ih_transaction; int /*<<< orphan*/  ih_flags; int /*<<< orphan*/  ih_length; } ;

/* Variables and functions */
 int ISNS_FLAG_FIRST ; 
 int ISNS_FLAG_LAST ; 
 int be16dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16enc (int /*<<< orphan*/ ,int) ; 
 int write (int,scalar_t__,int) ; 

int
isns_req_send(int s, struct isns_req *req)
{
	struct isns_hdr *hdr;
	int res;

	hdr = (struct isns_hdr *)req->ir_buf;
	be16enc(hdr->ih_length, req->ir_usedlen - sizeof(*hdr));
	be16enc(hdr->ih_flags, be16dec(hdr->ih_flags) |
	    ISNS_FLAG_LAST | ISNS_FLAG_FIRST);
	be16enc(hdr->ih_transaction, 0);
	be16enc(hdr->ih_sequence, 0);

	res = write(s, req->ir_buf, req->ir_usedlen);
	return ((res < 0) ? -1 : 0);
}