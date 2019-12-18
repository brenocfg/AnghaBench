#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  outlen; } ;
typedef  TYPE_1__ blake2s_state ;
struct TYPE_8__ {int /*<<< orphan*/  inner_length; } ;
typedef  TYPE_2__ blake2s_param ;

/* Variables and functions */
 int blake2s_init_param (TYPE_1__*,TYPE_2__ const*) ; 

__attribute__((used)) static int blake2sp_init_leaf_param( blake2s_state *S, const blake2s_param *P )
{
  int err = blake2s_init_param(S, P);
  S->outlen = P->inner_length;
  return err;
}