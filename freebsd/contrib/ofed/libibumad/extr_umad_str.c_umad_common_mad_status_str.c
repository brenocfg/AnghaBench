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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  UMAD_STATUS_ATTR_NOT_SUPPORTED 131 
#define  UMAD_STATUS_BAD_VERSION 130 
 int UMAD_STATUS_BUSY ; 
#define  UMAD_STATUS_INVALID_ATTR_VALUE 129 
 int UMAD_STATUS_INVALID_FIELD_MASK ; 
#define  UMAD_STATUS_METHOD_NOT_SUPPORTED 128 
 int UMAD_STATUS_REDIRECT ; 
 int be16toh (int /*<<< orphan*/ ) ; 

const char * umad_common_mad_status_str(__be16 _status)
{
	uint16_t status = be16toh(_status);

	if (status & UMAD_STATUS_BUSY)
		return ("Busy");

	if (status & UMAD_STATUS_REDIRECT)
		return ("Redirection required");

	switch(status & UMAD_STATUS_INVALID_FIELD_MASK) {
		case UMAD_STATUS_BAD_VERSION:
			return ("Bad Version");
		case UMAD_STATUS_METHOD_NOT_SUPPORTED:
			return ("Method not supported");
		case UMAD_STATUS_ATTR_NOT_SUPPORTED:
			return ("Method/Attribute combo not supported");
		case UMAD_STATUS_INVALID_ATTR_VALUE:
			return ("Invalid attribute/modifier field");
	}
	return ("Success");
}