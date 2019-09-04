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

/* Variables and functions */
 int ct_gif ; 
 int ct_jpeg ; 
 int ct_mov ; 
 int ct_mp3 ; 
 int ct_mp4 ; 
 int ct_pdf ; 
 int ct_png ; 
 int ct_unknown ; 
 int ct_webp ; 
 int /*<<< orphan*/  memcmp (unsigned char const*,char*,int) ; 

int detect_content_type (const unsigned char *const buff, int size) {
  const unsigned int *a = (const unsigned int *) buff;
  switch (buff[0]) {
    case 0:
      if (size >= 12) {
        if (a[0] == 0x14000000 && a[1] == 0x70797466 && a[2] == 0x20207471) {
          return ct_mov;
        }
        if (!(a[0] & 0x00ffffff) && a[1] == 0x70797466 && (a[2] & 0x00ffffff) == 0x0034706d) {
          return ct_mp4;
        }
      }
      break;
    case '%':
      if (size >= 4 && !memcmp (&buff[1], "PDF", 3)) {
        return ct_pdf;
      }
      break;
    case 'I':
      if (size >= 3 && !memcmp (&buff[1], "D3", 2)) {
        return ct_mp3;
      }
      break;
    case 'G':
      if (size >= 5 && !memcmp (&buff[1], "IF", 2)) {
        return ct_gif;
      }
      break;
    case 'R':
      if (size >= 4 && !memcmp (&buff[1], "IFF", 3)) {
        if (size >= 12 && !memcmp (&buff[8], "WEBP", 4)) {
          return ct_webp;
        }
        return ct_mp3;
      }
      break;
    case 0x89:
      if (size >= 4 && !memcmp (&buff[1], "PNG", 3)) {
        return ct_png;
      }
      break;
    case 0xff:
      if (size >= 2 && buff[1] == 0xd8) {
        return ct_jpeg;
      }
      if (size >= 2 && buff[1] >= 0xe0) {
        return ct_mp3;
      }
      break;
  }
  return ct_unknown;
}