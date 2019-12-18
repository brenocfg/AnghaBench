#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  handshake; int /*<<< orphan*/ * framing; int /*<<< orphan*/  baud_rate; } ;
typedef  TYPE_1__ COM_PARM ;

/* Variables and functions */
 int /*<<< orphan*/  get_lsb_int16 (unsigned char**) ; 
 int /*<<< orphan*/  get_lsb_long (unsigned char**) ; 

__attribute__((used)) static void
get_mbg_comparam(
	unsigned char **buffpp,
	COM_PARM *comparamp
	)
{
  size_t i;

  comparamp->baud_rate = get_lsb_long(buffpp);
  for (i = 0; i < sizeof(comparamp->framing); i++)
    {
      comparamp->framing[i] = *(*buffpp)++;
    }
  comparamp->handshake = get_lsb_int16(buffpp);
}