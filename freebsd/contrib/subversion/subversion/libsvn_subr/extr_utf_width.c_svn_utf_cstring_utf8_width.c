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
typedef  int apr_uint32_t ;

/* Variables and functions */
 int mk_wcwidth (int) ; 
 int /*<<< orphan*/  svn_utf__cstring_is_valid (char const*) ; 

int
svn_utf_cstring_utf8_width(const char *cstr)
{
  int width = 0;

  if (*cstr == '\0')
    return 0;

  /* Ensure the conversion below doesn't fail because of encoding errors. */
  if (!svn_utf__cstring_is_valid(cstr))
    return -1;

  /* Convert the UTF-8 string to UTF-32 (UCS4) which is the format
   * mk_wcwidth() expects, and get the width of each character.
   * We don't need much error checking since the input is valid UTF-8. */
  while (*cstr)
    {
      apr_uint32_t ucs;
      int nbytes;
      int lead_mask;
      int w;
      int i;

      if ((*cstr & 0x80) == 0)
        {
          nbytes = 1;
          lead_mask = 0x7f;
        }
      else if ((*cstr & 0xe0) == 0xc0)
        {
          nbytes = 2;
          lead_mask = 0x1f;
        }
      else if ((*cstr & 0xf0) == 0xe0)
        {
          nbytes = 3;
          lead_mask = 0x0f;
        }
      else if ((*cstr & 0xf8) == 0xf0)
        {
          nbytes = 4;
          lead_mask = 0x07;
        }
      else
        {
          /* RFC 3629 restricts UTF-8 to max 4 bytes per character. */
          return -1;
        }

      /* Parse character data from leading byte. */
      ucs = (apr_uint32_t)(*cstr & lead_mask);

      /* Parse character data from continuation bytes. */
      for (i = 1; i < nbytes; i++)
        {
          ucs <<= 6;
          ucs |= (cstr[i] & 0x3f);
        }

      cstr += nbytes;

      /* Determine the width of this character and add it to the total. */
      w = mk_wcwidth(ucs);
      if (w == -1)
        return -1;
      width += w;
    }

  return width;
}