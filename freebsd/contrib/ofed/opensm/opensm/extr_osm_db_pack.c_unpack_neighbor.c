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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strtok_r (char*,char*,char**) ; 
 unsigned long strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int unpack_neighbor(char *p_str, uint64_t *guid,
				  uint8_t *portnum)
{
	char tmp_str[24];
	char *p_num, *p_next;
	unsigned long tmp_port;

	strncpy(tmp_str, p_str, 23);
	tmp_str[23] = '\0';
	p_num = strtok_r(tmp_str, ":", &p_next);
	if (!p_num)
		return 1;
	if (guid)
		*guid = strtoull(p_num, NULL, 0);

	p_num = strtok_r(NULL, ":", &p_next);
	if (!p_num)
		return 1;
	if (portnum) {
		tmp_port = strtoul(p_num, NULL, 0);
		CL_ASSERT(tmp_port < 0x100);
		*portnum = (uint8_t) tmp_port;
	}

	return 0;
}