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
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  int apr_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_stringbuf_appendbyte (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (int /*<<< orphan*/ *,char*,int) ; 
 unsigned char* write_packed_uint_body (unsigned char*,int) ; 

__attribute__((used)) static void
write_packed_uint(svn_stringbuf_t* packed, apr_uint64_t value)
{
  if (value < 0x80)
    {
      svn_stringbuf_appendbyte(packed, (char)value);
    }
  else
    {
      unsigned char buffer[10];
      unsigned char *p = write_packed_uint_body(buffer, value);

      svn_stringbuf_appendbytes(packed, (char *)buffer, p - buffer);
    }
}