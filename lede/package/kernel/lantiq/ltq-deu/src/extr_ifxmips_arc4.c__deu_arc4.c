#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int GO; scalar_t__ BUS; } ;
struct arc4_t {int IDLEN; int ID3R; int ID2R; int ID1R; int ID0R; int OD3R; int OD2R; int OD1R; int OD0R; TYPE_1__ controlr; } ;

/* Variables and functions */
 scalar_t__ ARC4_START ; 
 int /*<<< orphan*/  CRTCL_SECT_END ; 
 int /*<<< orphan*/  CRTCL_SECT_START ; 

__attribute__((used)) static void _deu_arc4 (void *ctx_arg, u8 *out_arg, const u8 *in_arg,
            u8 *iv_arg, u32 nbytes, int encdec, int mode)
{
        volatile struct arc4_t *arc4 = (struct arc4_t *) ARC4_START;
        
        int i = 0;
        unsigned long flag;
        
#if 1 // need to handle nbytes not multiple of 16       
        volatile u32 tmp_array32[4];
        volatile u8 *tmp_ptr8;
        int remaining_bytes, j;
#endif

        CRTCL_SECT_START;

        arc4->IDLEN = nbytes;

#if 1
        while (i < nbytes) {
                arc4->ID3R = *((u32 *) in_arg + (i>>2) + 0);
                arc4->ID2R = *((u32 *) in_arg + (i>>2) + 1);    
                arc4->ID1R = *((u32 *) in_arg + (i>>2) + 2);
                arc4->ID0R = *((u32 *) in_arg + (i>>2) + 3);    
                
                arc4->controlr.GO = 1; 
                
                while (arc4->controlr.BUS) {
                      // this will not take long
                }

#if 1
                // need to handle nbytes not multiple of 16 
                tmp_array32[0] = arc4->OD3R;
                tmp_array32[1] = arc4->OD2R;
                tmp_array32[2] = arc4->OD1R;
                tmp_array32[3] = arc4->OD0R;

                remaining_bytes = nbytes - i;
                if (remaining_bytes > 16)
                     remaining_bytes = 16;
                
                tmp_ptr8 = (u8 *)&tmp_array32[0];
                for (j = 0; j < remaining_bytes; j++)
                     *out_arg++ = *tmp_ptr8++;
#else                                
                *((u32 *) out_arg + (i>>2) + 0) = arc4->OD3R;
                *((u32 *) out_arg + (i>>2) + 1) = arc4->OD2R;
                *((u32 *) out_arg + (i>>2) + 2) = arc4->OD1R;
                *((u32 *) out_arg + (i>>2) + 3) = arc4->OD0R;
#endif

                i += 16;
        }
#else // dma

#endif // dma

        CRTCL_SECT_END;
}