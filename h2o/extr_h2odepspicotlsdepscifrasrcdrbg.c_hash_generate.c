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
struct TYPE_3__ {int /*<<< orphan*/  hashsz; int /*<<< orphan*/  (* digest ) (int /*<<< orphan*/ *,int*) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,int*,size_t) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ cf_chash ;

/* Variables and functions */
 int CF_MAXHASH ; 
 size_t MIN (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  add (int*,size_t,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int*,size_t) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void hash_generate(const cf_chash *H,
                          uint8_t *data, size_t ndata, /* initialised with V */
                          void *out, size_t nout)
{
  cf_chash_ctx ctx;
  uint8_t w[CF_MAXHASH];
  uint8_t *bout = out;
  uint8_t one = 1;

  while (nout)
  {
    /* 4.1. w = Hash(data) */
    H->init(&ctx);
    H->update(&ctx, data, ndata);
    H->digest(&ctx, w);

    /* 4.2. W = W || w */
    size_t take = MIN(H->hashsz, nout);
    memcpy(bout, w, take);
    bout += take;
    nout -= take;

    /* 4.3. data = (data + 1) mod 2 ^ seedlen */
    add(data, ndata, &one, sizeof one);
  }
}