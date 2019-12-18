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
struct fw_request {int /*<<< orphan*/ * request_header; } ;

/* Variables and functions */
#define  EXTCODE_FETCH_ADD 134 
#define  EXTCODE_LITTLE_ADD 133 
 int HEADER_GET_DATA_LENGTH (int /*<<< orphan*/ ) ; 
 int HEADER_GET_EXTENDED_TCODE (int /*<<< orphan*/ ) ; 
 int HEADER_GET_TCODE (int /*<<< orphan*/ ) ; 
#define  TCODE_LOCK_REQUEST 132 
#define  TCODE_READ_BLOCK_REQUEST 131 
#define  TCODE_READ_QUADLET_REQUEST 130 
#define  TCODE_WRITE_BLOCK_REQUEST 129 
#define  TCODE_WRITE_QUADLET_REQUEST 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 

int fw_get_response_length(struct fw_request *r)
{
	int tcode, ext_tcode, data_length;

	tcode = HEADER_GET_TCODE(r->request_header[0]);

	switch (tcode) {
	case TCODE_WRITE_QUADLET_REQUEST:
	case TCODE_WRITE_BLOCK_REQUEST:
		return 0;

	case TCODE_READ_QUADLET_REQUEST:
		return 4;

	case TCODE_READ_BLOCK_REQUEST:
		data_length = HEADER_GET_DATA_LENGTH(r->request_header[3]);
		return data_length;

	case TCODE_LOCK_REQUEST:
		ext_tcode = HEADER_GET_EXTENDED_TCODE(r->request_header[3]);
		data_length = HEADER_GET_DATA_LENGTH(r->request_header[3]);
		switch (ext_tcode) {
		case EXTCODE_FETCH_ADD:
		case EXTCODE_LITTLE_ADD:
			return data_length;
		default:
			return data_length / 2;
		}

	default:
		WARN(1, "wrong tcode %d\n", tcode);
		return 0;
	}
}