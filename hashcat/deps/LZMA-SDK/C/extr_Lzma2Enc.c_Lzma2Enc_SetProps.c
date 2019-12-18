#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ lc; scalar_t__ lp; } ;
struct TYPE_8__ {TYPE_1__ lzmaProps; } ;
struct TYPE_9__ {TYPE_2__ props; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CLzmaEncProps ;
typedef  TYPE_2__ CLzma2EncProps ;
typedef  scalar_t__ CLzma2EncHandle ;
typedef  TYPE_3__ CLzma2Enc ;

/* Variables and functions */
 scalar_t__ LZMA2_LCLP_MAX ; 
 int /*<<< orphan*/  Lzma2EncProps_Normalize (TYPE_2__*) ; 
 int /*<<< orphan*/  LzmaEncProps_Normalize (TYPE_1__*) ; 
 int /*<<< orphan*/  SZ_ERROR_PARAM ; 
 int /*<<< orphan*/  SZ_OK ; 

SRes Lzma2Enc_SetProps(CLzma2EncHandle pp, const CLzma2EncProps *props)
{
  CLzma2Enc *p = (CLzma2Enc *)pp;
  CLzmaEncProps lzmaProps = props->lzmaProps;
  LzmaEncProps_Normalize(&lzmaProps);
  if (lzmaProps.lc + lzmaProps.lp > LZMA2_LCLP_MAX)
    return SZ_ERROR_PARAM;
  p->props = *props;
  Lzma2EncProps_Normalize(&p->props);
  return SZ_OK;
}