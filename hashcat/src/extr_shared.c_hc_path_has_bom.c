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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,char const*,char*) ; 
 size_t hc_fread (int*,int,int,int /*<<< orphan*/ *) ; 

bool hc_path_has_bom (const char *path)
{
  u8 buf[8] = { 0 };

  HCFILE fp;

  if (hc_fopen (&fp, path, "rb") == false) return false;

  const size_t nread = hc_fread (buf, 1, sizeof (buf), &fp);

  hc_fclose (&fp);

  if (nread < 1) return false;

  /* signatures from https://en.wikipedia.org/wiki/Byte_order_mark#Byte_order_marks_by_encoding */

  // utf-8

  if ((buf[0] == 0xef)
   && (buf[1] == 0xbb)
   && (buf[2] == 0xbf)) return true;

  // utf-16

  if ((buf[0] == 0xfe)
   && (buf[1] == 0xff)) return true;

  if ((buf[0] == 0xff)
   && (buf[1] == 0xfe)) return true;

  // utf-32

  if ((buf[0] == 0x00)
   && (buf[1] == 0x00)
   && (buf[2] == 0xfe)
   && (buf[3] == 0xff)) return true;

  if ((buf[0] == 0xff)
   && (buf[1] == 0xfe)
   && (buf[2] == 0x00)
   && (buf[3] == 0x00)) return true;

  // utf-7

  if ((buf[0] == 0x2b)
   && (buf[1] == 0x2f)
   && (buf[2] == 0x76)
   && (buf[3] == 0x38)) return true;

  if ((buf[0] == 0x2b)
   && (buf[1] == 0x2f)
   && (buf[2] == 0x76)
   && (buf[3] == 0x39)) return true;

  if ((buf[0] == 0x2b)
   && (buf[1] == 0x2f)
   && (buf[2] == 0x76)
   && (buf[3] == 0x2b)) return true;

  if ((buf[0] == 0x2b)
   && (buf[1] == 0x2f)
   && (buf[2] == 0x76)
   && (buf[3] == 0x2f)) return true;

  if ((buf[0] == 0x2b)
   && (buf[1] == 0x2f)
   && (buf[2] == 0x76)
   && (buf[3] == 0x38)
   && (buf[4] == 0x2d)) return true;

  // utf-1

  if ((buf[0] == 0xf7)
   && (buf[1] == 0x64)
   && (buf[2] == 0x4c)) return true;

  // utf-ebcdic

  if ((buf[0] == 0xdd)
   && (buf[1] == 0x73)
   && (buf[2] == 0x66)
   && (buf[3] == 0x73)) return true;

  // scsu

  if ((buf[0] == 0x0e)
   && (buf[1] == 0xfe)
   && (buf[2] == 0xff)) return true;

  // bocu-1

  if ((buf[0] == 0xfb)
   && (buf[1] == 0xee)
   && (buf[2] == 0x28)) return true;

  // gb-18030

  if ((buf[0] == 0x84)
   && (buf[1] == 0x31)
   && (buf[2] == 0x95)
   && (buf[3] == 0x33)) return true;

  return false;
}