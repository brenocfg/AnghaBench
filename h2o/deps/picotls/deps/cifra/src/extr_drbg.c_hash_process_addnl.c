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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  cf_chash_ctx ;
struct TYPE_3__ {int /*<<< orphan*/  hashsz; int /*<<< orphan*/  (* digest ) (int /*<<< orphan*/ *,int*) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,void const*,size_t) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ cf_chash ;

/* Variables and functions */
 int CF_MAXHASH ; 
 int /*<<< orphan*/  add (int*,size_t,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int*,size_t) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void hash_process_addnl(const cf_chash *H,
                               const void *input, size_t ninput,
                               uint8_t *V, size_t nV)
{
  if (!ninput)
    return;

  /* 2.1. w = Hash(0x02 || V || additional_input) */
  uint8_t two = 2;
  uint8_t w[CF_MAXHASH];
  cf_chash_ctx ctx;
  H->init(&ctx);
  H->update(&ctx, &two, sizeof two);
  H->update(&ctx, V, nV);
  H->update(&ctx, input, ninput);
  H->digest(&ctx, w);

  /* 2.2. V = (V + w) mod 2 ^ seedlen */
  add(V, nV, w, H->hashsz);
}