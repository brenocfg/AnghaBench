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
typedef  int svn_boolean_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int FALSE ; 
 int FSM_START ; 
 char* first_non_fsm_start_char (char const*,int) ; 
 int** machine ; 
 int* octet_category ; 

svn_boolean_t
svn_utf__is_valid(const char *data, apr_size_t len)
{
  const char *end = data + len;
  int state = FSM_START;

  if (!data)
    return FALSE;

  data = first_non_fsm_start_char(data, len);

  while (data < end)
    {
      unsigned char octet = *data++;
      int category = octet_category[octet];
      state = machine[state][category];
    }
  return state == FSM_START;
}