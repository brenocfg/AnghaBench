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
typedef  int svn_boolean_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int FALSE ; 

svn_boolean_t
svn_io_is_binary_data(const void *data, apr_size_t len)
{
  const unsigned char *buf = data;

  if (len == 3 && buf[0] == 0xEF && buf[1] == 0xBB && buf[2] == 0xBF)
    {
      /* This is an empty UTF-8 file which only contains the UTF-8 BOM.
       * Treat it as plain text. */
      return FALSE;
    }

  /* Right now, this function is going to be really stupid.  It's
     going to examine the block of data, and make sure that 15%
     of the bytes are such that their value is in the ranges 0x07-0x0D
     or 0x20-0x7F, and that none of those bytes is 0x00.  If those
     criteria are not met, we're calling it binary.

     NOTE:  Originally, I intended to target 85% of the bytes being in
     the specified ranges, but I flubbed the condition.  At any rate,
     folks aren't complaining, so I'm not sure that it's worth
     adjusting this retroactively now.  --cmpilato  */
  if (len > 0)
    {
      apr_size_t i;
      apr_size_t binary_count = 0;

      /* Run through the data we've read, counting the 'binary-ish'
         bytes.  HINT: If we see a 0x00 byte, we'll set our count to its
         max and stop reading the file. */
      for (i = 0; i < len; i++)
        {
          if (buf[i] == 0)
            {
              binary_count = len;
              break;
            }
          if ((buf[i] < 0x07)
              || ((buf[i] > 0x0D) && (buf[i] < 0x20))
              || (buf[i] > 0x7F))
            {
              binary_count++;
            }
        }

      return (((binary_count * 1000) / len) > 850);
    }

  return FALSE;
}