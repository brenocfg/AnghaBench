#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  svid; int /*<<< orphan*/  oh; int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_offset; int /*<<< orphan*/  exclusive; } ;
struct file_lock {int /*<<< orphan*/  client_name; TYPE_1__ client; int /*<<< orphan*/  flags; int /*<<< orphan*/  status; int /*<<< orphan*/  nsm_status; int /*<<< orphan*/  client_cookie; int /*<<< orphan*/  filehandle; } ;
typedef  int /*<<< orphan*/  hbuff ;
typedef  int /*<<< orphan*/  cbuff ;

/* Variables and functions */
 int MAXBUFFERSIZE ; 
 int debug_level ; 
 int /*<<< orphan*/  debuglog (char*,...) ; 
 int /*<<< orphan*/  dump_netobj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_static_object (unsigned char*,int,char*,int,char*,int) ; 

void
dump_filelock(const struct file_lock *fl)
{
#ifdef DUMP_FILELOCK_VERBOSE
	char hbuff[MAXBUFFERSIZE*2];
	char cbuff[MAXBUFFERSIZE];
#endif

	if (debug_level < 2) {
		return;
	}

	if (fl != NULL) {
		debuglog("Dumping file lock structure @ %p\n", fl);

#ifdef DUMP_FILELOCK_VERBOSE
		dump_static_object((unsigned char *)&fl->filehandle,
		    sizeof(fl->filehandle), hbuff, sizeof(hbuff),
		    cbuff, sizeof(cbuff));
		debuglog("Filehandle: %8s  :::  %8s\n", hbuff, cbuff);
#endif

		debuglog("Dumping nlm4_holder:\n"
		    "exc: %x  svid: %x  offset:len %llx:%llx\n",
		    fl->client.exclusive, fl->client.svid,
		    fl->client.l_offset, fl->client.l_len);

#ifdef DUMP_FILELOCK_VERBOSE
		debuglog("Dumping client identity:\n");
		dump_netobj(&fl->client.oh);

		debuglog("Dumping client cookie:\n");
		dump_netobj(&fl->client_cookie);

		debuglog("nsm: %d  status: %d  flags: %d  svid: %x"
		    "  client_name: %s\n", fl->nsm_status, fl->status,
		    fl->flags, fl->client.svid, fl->client_name);
#endif
	} else {
		debuglog("NULL file lock structure\n");
	}
}