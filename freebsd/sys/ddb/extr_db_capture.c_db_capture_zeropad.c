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
typedef  int /*<<< orphan*/  u_int ;

/* Variables and functions */
 int TEXTDUMP_BLOCKSIZE ; 
 int /*<<< orphan*/  bzero (int,int /*<<< orphan*/ ) ; 
 int db_capture_buf ; 
 int db_capture_bufoff ; 
 int /*<<< orphan*/  db_capture_bufpadding ; 
 int db_capture_bufsize ; 
 int /*<<< orphan*/  min (int,int) ; 

__attribute__((used)) static void
db_capture_zeropad(void)
{
	u_int len;

	len = min(TEXTDUMP_BLOCKSIZE, (db_capture_bufsize -
	    db_capture_bufoff) % TEXTDUMP_BLOCKSIZE);
	bzero(db_capture_buf + db_capture_bufoff, len);
	db_capture_bufpadding = len;
}