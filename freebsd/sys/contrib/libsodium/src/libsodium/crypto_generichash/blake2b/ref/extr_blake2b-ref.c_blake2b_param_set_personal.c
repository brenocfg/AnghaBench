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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  personal; } ;
typedef  TYPE_1__ blake2b_param ;

/* Variables and functions */
 int /*<<< orphan*/  BLAKE2B_PERSONALBYTES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
blake2b_param_set_personal(blake2b_param *P,
                           const uint8_t  personal[BLAKE2B_PERSONALBYTES])
{
    memcpy(P->personal, personal, BLAKE2B_PERSONALBYTES);
    return 0;
}