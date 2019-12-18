#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64b_t ;
typedef  int /*<<< orphan*/  u08b_t ;
typedef  int /*<<< orphan*/  X ;
struct TYPE_7__ {size_t bCnt; int hashBitLen; int /*<<< orphan*/ * T; } ;
struct TYPE_6__ {int /*<<< orphan*/ * X; TYPE_3__ h; int /*<<< orphan*/ * b; } ;
typedef  TYPE_1__ Skein1024_Ctxt_t ;

/* Variables and functions */
 int /*<<< orphan*/  OUT_FINAL ; 
 size_t SKEIN1024_BLOCK_BYTES ; 
 int SKEIN1024_STATE_WORDS ; 
 int /*<<< orphan*/  SKEIN_FAIL ; 
 int SKEIN_SUCCESS ; 
 int /*<<< orphan*/  SKEIN_T1_FLAG_FINAL ; 
 int /*<<< orphan*/  Skein1024_Process_Block (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  Skein_Assert (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Skein_Put64_LSB_First (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  Skein_Show_Final (int,TYPE_3__*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Skein_Start_New_Type (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Skein_Swap64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int Skein1024_Final(Skein1024_Ctxt_t *ctx, u08b_t *hashVal)
    {
    size_t i,n,byteCnt;
    u64b_t X[SKEIN1024_STATE_WORDS];
    Skein_Assert(ctx->h.bCnt <= SKEIN1024_BLOCK_BYTES,SKEIN_FAIL);    /* catch uninitialized context */

    ctx->h.T[1] |= SKEIN_T1_FLAG_FINAL;                 /* tag as the final block */
    if (ctx->h.bCnt < SKEIN1024_BLOCK_BYTES)            /* zero pad b[] if necessary */
        memset(&ctx->b[ctx->h.bCnt],0,SKEIN1024_BLOCK_BYTES - ctx->h.bCnt);

    Skein1024_Process_Block(ctx,ctx->b,1,ctx->h.bCnt);  /* process the final block */
    
    /* now output the result */
    byteCnt = (ctx->h.hashBitLen + 7) >> 3;             /* total number of output bytes */

    /* run Threefish in "counter mode" to generate output */
    memset(ctx->b,0,sizeof(ctx->b));  /* zero out b[], so it can hold the counter */
    memcpy(X,ctx->X,sizeof(X));       /* keep a local copy of counter mode "key" */
    for (i=0;i*SKEIN1024_BLOCK_BYTES < byteCnt;i++)
        {
        ((u64b_t *)ctx->b)[0]= Skein_Swap64((u64b_t) i); /* build the counter block */
        Skein_Start_New_Type(ctx,OUT_FINAL);
        Skein1024_Process_Block(ctx,ctx->b,1,sizeof(u64b_t)); /* run "counter mode" */
        n = byteCnt - i*SKEIN1024_BLOCK_BYTES;   /* number of output bytes left to go */
        if (n >= SKEIN1024_BLOCK_BYTES)
            n  = SKEIN1024_BLOCK_BYTES;
        Skein_Put64_LSB_First(hashVal+i*SKEIN1024_BLOCK_BYTES,ctx->X,n);   /* "output" the ctr mode bytes */
        Skein_Show_Final(1024,&ctx->h,n,hashVal+i*SKEIN1024_BLOCK_BYTES);
        memcpy(ctx->X,X,sizeof(X));   /* restore the counter mode key for next time */
        }
    return SKEIN_SUCCESS;
    }