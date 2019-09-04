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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  bit_rate; } ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
 int /*<<< orphan*/  htobe16 (int) ; 
 int /*<<< orphan*/  htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 

__attribute__((used)) static void restore_mpeg4_esds(AVCodecParameters *codecpar,
                                 uint8_t *p_buf, size_t i_buf_size,
                                 size_t i_es_dscr_length, size_t i_dec_dscr_length,
                                 uint8_t *p_esds_buf)
{
    p_esds_buf[0] = 0x03;
    p_esds_buf[1] = 0x80;
    p_esds_buf[2] = 0x80;
    p_esds_buf[3] = 0x80;
    p_esds_buf[4] = i_es_dscr_length;
    uint16_t *es_id = (uint16_t *)&p_esds_buf[5];
    *es_id = htobe16(1);
    
    p_esds_buf[8] = 0x04;
    p_esds_buf[9] = 0x80;
    p_esds_buf[10] = 0x80;
    p_esds_buf[11] = 0x80;
    p_esds_buf[12] = i_dec_dscr_length;
    p_esds_buf[13] = 0x20;
    p_esds_buf[14] = 0x11;
    uint32_t *max_br = (uint32_t *)&p_esds_buf[18];
    uint32_t *avg_br = (uint32_t *)&p_esds_buf[22];
    *max_br = *avg_br = htobe32(codecpar->bit_rate);

    p_esds_buf[26] = 0x05;
    p_esds_buf[27] = 0x80;
    p_esds_buf[28] = 0x80;
    p_esds_buf[29] = 0x80;
    p_esds_buf[30] = i_buf_size;
    memcpy(&p_esds_buf[31], p_buf, i_buf_size);

    p_esds_buf[31+i_buf_size] = 0x06;
    p_esds_buf[31+i_buf_size+1] = 0x80;
    p_esds_buf[31+i_buf_size+2] = 0x80;
    p_esds_buf[31+i_buf_size+3] = 0x80;
    p_esds_buf[31+i_buf_size+4] = 0x01;
    p_esds_buf[31+i_buf_size+5] = 0x02;
}