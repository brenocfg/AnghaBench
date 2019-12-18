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
typedef  int autr_state_type ;

/* Variables and functions */
#define  AUTR_STATE_ADDPEND 133 
#define  AUTR_STATE_MISSING 132 
#define  AUTR_STATE_REMOVED 131 
#define  AUTR_STATE_REVOKED 130 
#define  AUTR_STATE_START 129 
#define  AUTR_STATE_VALID 128 

__attribute__((used)) static const char*
trustanchor_state2str(autr_state_type s)
{
        switch (s) {
                case AUTR_STATE_START:       return "  START  ";
                case AUTR_STATE_ADDPEND:     return " ADDPEND ";
                case AUTR_STATE_VALID:       return "  VALID  ";
                case AUTR_STATE_MISSING:     return " MISSING ";
                case AUTR_STATE_REVOKED:     return " REVOKED ";
                case AUTR_STATE_REMOVED:     return " REMOVED ";
        }
        return " UNKNOWN ";
}