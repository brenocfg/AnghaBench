#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int GZIP_HEAD_FCOMMENT_BIT ; 
 int GZIP_HEAD_FEXTRA_BIT ; 
 int GZIP_HEAD_FEXTRA_SHIFT ; 
 int GZIP_HEAD_FHCRC_BIT ; 
 int GZIP_HEAD_FHCRC_SIZE ; 
 int GZIP_HEAD_FLG_SHIFT ; 
 int GZIP_HEAD_FNAME_BIT ; 
 int get_comment_field_size (int const*) ; 
 int get_extra_field_size (int const*) ; 
 int get_name_field_size (int const*) ; 

__attribute__((used)) static u32 __get_gzip_head_size(const u8 *src)
{
	u8 head_flg = *(src + GZIP_HEAD_FLG_SHIFT);
	u32 size = GZIP_HEAD_FEXTRA_SHIFT;

	if (head_flg & GZIP_HEAD_FEXTRA_BIT)
		size += get_extra_field_size(src + size);
	if (head_flg & GZIP_HEAD_FNAME_BIT)
		size += get_name_field_size(src + size);
	if (head_flg & GZIP_HEAD_FCOMMENT_BIT)
		size += get_comment_field_size(src + size);
	if (head_flg & GZIP_HEAD_FHCRC_BIT)
		size += GZIP_HEAD_FHCRC_SIZE;

	return size;
}