#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {int length; } ;

/* Variables and functions */
 scalar_t__ CALL_JQ ; 
 scalar_t__ TAIL_CALL_JQ ; 
 TYPE_1__* opcode_describe (scalar_t__) ; 

int bytecode_operation_length(uint16_t* codeptr) {
  int length = opcode_describe(*codeptr)->length;
  if (*codeptr == CALL_JQ || *codeptr == TAIL_CALL_JQ) {
    length += codeptr[1] * 2;
  }
  return length;
}