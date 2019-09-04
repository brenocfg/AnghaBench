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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_ERR_MSG_INVALIDARG ; 
#define  MRB_DEBUG_INVALID_ARGUMENT 128 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_api_common_error(int32_t error)
{
  switch(error) {
    case MRB_DEBUG_INVALID_ARGUMENT:
      puts(BREAK_ERR_MSG_INVALIDARG);
      break;
    default:
      break;
  }
}