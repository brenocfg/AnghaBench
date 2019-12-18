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
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  UMAD_ATTR_CLASS_PORT_INFO 130 
#define  UMAD_ATTR_INFORM_INFO 129 
#define  UMAD_ATTR_NOTICE 128 
 int be16toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *umad_common_attr_str(__be16 attr_id)
{
	switch(be16toh(attr_id)) {
		case UMAD_ATTR_CLASS_PORT_INFO:
			return "Class Port Info";
		case UMAD_ATTR_NOTICE:
			return "Notice";
		case UMAD_ATTR_INFORM_INFO:
			return "Inform Info";
		default:
			return "<unknown>";
	}
}