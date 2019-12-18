#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  blake2b_state ;
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int member_2; int member_3; TYPE_3__ member_10; TYPE_2__ member_9; TYPE_1__ member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ blake2b_param ;

/* Variables and functions */
 size_t BLAKE2B_OUTBYTES ; 
 int blake2b_init_param (int /*<<< orphan*/ *,TYPE_4__ const*) ; 

int blake2b_init( blake2b_state *S, size_t outlen )
{
  if ( ( !outlen ) || ( outlen > BLAKE2B_OUTBYTES ) ) return -1;

  const blake2b_param P =
  {
    ( uint8_t ) outlen,
    0,
    1,
    1,
    0,
    0,
    0,
    0,
    {0},
    {0},
    {0}
  };
  return blake2b_init_param( S, &P );
}