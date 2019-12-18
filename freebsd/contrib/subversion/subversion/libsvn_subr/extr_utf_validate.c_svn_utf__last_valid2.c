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
typedef  int apr_size_t ;

/* Variables and functions */
#define  FSM_808F 136 
#define  FSM_809F 135 
#define  FSM_80BF 134 
#define  FSM_80BF80BF 133 
#define  FSM_80BF80BF80BF 132 
#define  FSM_90BF 131 
#define  FSM_A0BF 130 
#define  FSM_ERROR 129 
#define  FSM_START 128 
 char* first_non_fsm_start_char (char const*,int) ; 

const char *
svn_utf__last_valid2(const char *data, apr_size_t len)
{
  const char *start = first_non_fsm_start_char(data, len);
  const char *end = data + len;
  int state = FSM_START;

  data = start;
  while (data < end)
    {
      unsigned char octet = *data++;
      switch (state)
        {
        case FSM_START:
          if (octet <= 0x7F)
            break;
          else if (octet <= 0xC1)
            state = FSM_ERROR;
          else if (octet <= 0xDF)
            state = FSM_80BF;
          else if (octet == 0xE0)
            state = FSM_A0BF;
          else if (octet <= 0xEC)
            state = FSM_80BF80BF;
          else if (octet == 0xED)
            state = FSM_809F;
          else if (octet <= 0xEF)
            state = FSM_80BF80BF;
          else if (octet == 0xF0)
            state = FSM_90BF;
          else if (octet <= 0xF3)
            state = FSM_80BF80BF80BF;
          else if (octet <= 0xF4)
            state = FSM_808F;
          else
            state = FSM_ERROR;
          break;
        case FSM_80BF:
          if (octet >= 0x80 && octet <= 0xBF)
            state = FSM_START;
          else
            state = FSM_ERROR;
          break;
        case FSM_A0BF:
          if (octet >= 0xA0 && octet <= 0xBF)
            state = FSM_80BF;
          else
            state = FSM_ERROR;
          break;
        case FSM_80BF80BF:
          if (octet >= 0x80 && octet <= 0xBF)
            state = FSM_80BF;
          else
            state = FSM_ERROR;
          break;
        case FSM_809F:
          if (octet >= 0x80 && octet <= 0x9F)
            state = FSM_80BF;
          else
            state = FSM_ERROR;
          break;
        case FSM_90BF:
          if (octet >= 0x90 && octet <= 0xBF)
            state = FSM_80BF80BF;
          else
            state = FSM_ERROR;
          break;
        case FSM_80BF80BF80BF:
          if (octet >= 0x80 && octet <= 0xBF)
            state = FSM_80BF80BF;
          else
            state = FSM_ERROR;
          break;
        case FSM_808F:
          if (octet >= 0x80 && octet <= 0x8F)
            state = FSM_80BF80BF;
          else
            state = FSM_ERROR;
          break;
        default:
        case FSM_ERROR:
          return start;
        }
      if (state == FSM_START)
        start = data;
    }
  return start;
}