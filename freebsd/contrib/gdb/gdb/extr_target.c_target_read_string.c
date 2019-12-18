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
typedef  int CORE_ADDR ;

/* Variables and functions */
 int MIN (int,int) ; 
 int target_xfer_memory (int,char*,int,int /*<<< orphan*/ ) ; 
 char* xmalloc (int) ; 
 char* xrealloc (char*,int) ; 

int
target_read_string (CORE_ADDR memaddr, char **string, int len, int *errnop)
{
  int tlen, origlen, offset, i;
  char buf[4];
  int errcode = 0;
  char *buffer;
  int buffer_allocated;
  char *bufptr;
  unsigned int nbytes_read = 0;

  /* Small for testing.  */
  buffer_allocated = 4;
  buffer = xmalloc (buffer_allocated);
  bufptr = buffer;

  origlen = len;

  while (len > 0)
    {
      tlen = MIN (len, 4 - (memaddr & 3));
      offset = memaddr & 3;

      errcode = target_xfer_memory (memaddr & ~3, buf, 4, 0);
      if (errcode != 0)
	{
	  /* The transfer request might have crossed the boundary to an
	     unallocated region of memory. Retry the transfer, requesting
	     a single byte.  */
	  tlen = 1;
	  offset = 0;
	  errcode = target_xfer_memory (memaddr, buf, 1, 0);
	  if (errcode != 0)
	    goto done;
	}

      if (bufptr - buffer + tlen > buffer_allocated)
	{
	  unsigned int bytes;
	  bytes = bufptr - buffer;
	  buffer_allocated *= 2;
	  buffer = xrealloc (buffer, buffer_allocated);
	  bufptr = buffer + bytes;
	}

      for (i = 0; i < tlen; i++)
	{
	  *bufptr++ = buf[i + offset];
	  if (buf[i + offset] == '\000')
	    {
	      nbytes_read += i + 1;
	      goto done;
	    }
	}

      memaddr += tlen;
      len -= tlen;
      nbytes_read += tlen;
    }
done:
  if (errnop != NULL)
    *errnop = errcode;
  if (string != NULL)
    *string = buffer;
  return nbytes_read;
}