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
typedef  int /*<<< orphan*/  ULONGEST ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 char* alloca (long) ; 
 int /*<<< orphan*/  errno ; 
 int get_memory_read_packet_size () ; 
 int /*<<< orphan*/  getpkt (char*,long,int /*<<< orphan*/ ) ; 
 int hex2bin (char*,char*,int) ; 
 int /*<<< orphan*/  hexnumstr (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isxdigit (char) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  putpkt (char*) ; 
 scalar_t__ remote_address_masked (scalar_t__) ; 

int
remote_read_bytes (CORE_ADDR memaddr, char *myaddr, int len)
{
  char *buf;
  int max_buf_size;		/* Max size of packet output buffer */
  long sizeof_buf;
  int origlen;

  /* Create a buffer big enough for this packet. */
  max_buf_size = get_memory_read_packet_size ();
  sizeof_buf = max_buf_size + 1; /* Space for trailing NUL */
  buf = alloca (sizeof_buf);

  origlen = len;
  while (len > 0)
    {
      char *p;
      int todo;
      int i;

      todo = min (len, max_buf_size / 2);	/* num bytes that will fit */

      /* construct "m"<memaddr>","<len>" */
      /* sprintf (buf, "m%lx,%x", (unsigned long) memaddr, todo); */
      memaddr = remote_address_masked (memaddr);
      p = buf;
      *p++ = 'm';
      p += hexnumstr (p, (ULONGEST) memaddr);
      *p++ = ',';
      p += hexnumstr (p, (ULONGEST) todo);
      *p = '\0';

      putpkt (buf);
      getpkt (buf, sizeof_buf, 0);

      if (buf[0] == 'E'
	  && isxdigit (buf[1]) && isxdigit (buf[2])
	  && buf[3] == '\0')
	{
	  /* There is no correspondance between what the remote protocol uses
	     for errors and errno codes.  We would like a cleaner way of
	     representing errors (big enough to include errno codes, bfd_error
	     codes, and others).  But for now just return EIO.  */
	  errno = EIO;
	  return 0;
	}

      /* Reply describes memory byte by byte,
         each byte encoded as two hex characters.  */

      p = buf;
      if ((i = hex2bin (p, myaddr, todo)) < todo)
	{
	  /* Reply is short.  This means that we were able to read
	     only part of what we wanted to. */
	  return i + (origlen - len);
	}
      myaddr += todo;
      memaddr += todo;
      len -= todo;
    }
  return origlen;
}