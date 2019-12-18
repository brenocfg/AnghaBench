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
typedef  size_t u_int ;
struct ahd_softc {size_t msgout_len; size_t* msgout_buf; size_t msgout_index; } ;
typedef  scalar_t__ ahd_msgtype ;

/* Variables and functions */
 scalar_t__ AHDMSG_1B ; 
 scalar_t__ AHDMSG_EXT ; 
 int FALSE ; 
 size_t MSG_EXTENDED ; 
 size_t MSG_IDENTIFYFLAG ; 
 size_t MSG_IGN_WIDE_RESIDUE ; 
 size_t MSG_SIMPLE_TASK ; 
 int TRUE ; 

__attribute__((used)) static int
ahd_sent_msg(struct ahd_softc *ahd, ahd_msgtype type, u_int msgval, int full)
{
	int found;
	u_int index;

	found = FALSE;
	index = 0;

	while (index < ahd->msgout_len) {
		if (ahd->msgout_buf[index] == MSG_EXTENDED) {
			u_int end_index;

			end_index = index + 1 + ahd->msgout_buf[index + 1];
			if (ahd->msgout_buf[index+2] == msgval
			 && type == AHDMSG_EXT) {

				if (full) {
					if (ahd->msgout_index > end_index)
						found = TRUE;
				} else if (ahd->msgout_index > index)
					found = TRUE;
			}
			index = end_index;
		} else if (ahd->msgout_buf[index] >= MSG_SIMPLE_TASK
			&& ahd->msgout_buf[index] <= MSG_IGN_WIDE_RESIDUE) {

			/* Skip tag type and tag id or residue param*/
			index += 2;
		} else {
			/* Single byte message */
			if (type == AHDMSG_1B
			 && ahd->msgout_index > index
			 && (ahd->msgout_buf[index] == msgval
			  || ((ahd->msgout_buf[index] & MSG_IDENTIFYFLAG) != 0
			   && msgval == MSG_IDENTIFYFLAG)))
				found = TRUE;
			index++;
		}

		if (found)
			break;
	}
	return (found);
}