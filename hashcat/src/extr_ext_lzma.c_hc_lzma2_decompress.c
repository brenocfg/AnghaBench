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
struct TYPE_3__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  SizeT ;
typedef  TYPE_1__ ISzAlloc ;
typedef  int /*<<< orphan*/  ELzmaStatus ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_FINISH_ANY ; 
 int Lzma2Decode (unsigned char*,int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  hc_lzma_alloc ; 
 int /*<<< orphan*/  hc_lzma_free ; 

int hc_lzma2_decompress (const unsigned char *in, SizeT *in_len, unsigned char *out, SizeT *out_len, const char *props)
{
  ISzAlloc hc_lzma_mem_alloc = {hc_lzma_alloc, hc_lzma_free};

  ELzmaStatus status;

  // parameters to Lzma2Decode (): unsigned char *dest, size_t *destLen, const unsigned char *src,
  // size_t *srcLen, const unsigned char props, ELzmaFinishMode finishMode, ELzmaStatus status, ISzAlloc *alloc

  return Lzma2Decode (out, out_len, in, in_len, (Byte) props[0], LZMA_FINISH_ANY, &status, &hc_lzma_mem_alloc);
}