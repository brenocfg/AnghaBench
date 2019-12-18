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
typedef  void* uint16_t ;
struct input_event {scalar_t__ value; void* code; void* type; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  ie ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (struct input_event*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ write (scalar_t__,struct input_event*,int) ; 

__attribute__((used)) static int32_t
uinput_write_event(int32_t fd, uint16_t type, uint16_t code, int32_t value)
{
	struct input_event ie;

	assert(fd >= 0);

	memset(&ie, 0, sizeof(ie));
	ie.type = type;
	ie.code = code;
	ie.value = value;
	return (write(fd, &ie, sizeof(ie)));
}