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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static const char *guid_str(__be64 _node_guid, char *str)
{
	uint64_t node_guid = be64toh(_node_guid);
	sprintf(str, "%04x:%04x:%04x:%04x",
		(unsigned) (node_guid >> 48) & 0xffff,
		(unsigned) (node_guid >> 32) & 0xffff,
		(unsigned) (node_guid >> 16) & 0xffff,
		(unsigned) (node_guid >>  0) & 0xffff);
	return str;
}