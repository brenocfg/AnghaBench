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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int htonl (int) ; 

__attribute__((used)) static void
marker_fill(uint64_t* buf, int file_ofs, size_t len, int is_follower){
  int ofs;
  uint32_t lead_mark = 0x4441454c;  //"LEAD" in little endian
  uint32_t follow_mark = 0x4c4c4f46; //"FOLL" in little endian
  for (ofs = file_ofs; ofs < file_ofs + len; ofs += sizeof(uint64_t)){
    uint64_t mark = ((is_follower ? 
          (uint64_t)follow_mark : (uint64_t)lead_mark) << (uint64_t)32) |
      htonl((ofs & 0xFFFFFFFF));
    int buf_idx = (ofs - file_ofs) / sizeof(uint64_t);
    buf[buf_idx] = mark;
  }
}