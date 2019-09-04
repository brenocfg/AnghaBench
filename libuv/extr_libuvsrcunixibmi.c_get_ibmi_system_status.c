#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct _errcode   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  errcode ;
struct _errcode {int bytes_provided; int bytes_available; char* msgid; } ;
typedef  TYPE_1__ SSTS0200 ;
typedef  int /*<<< orphan*/  ILEpointer ;

/* Variables and functions */
 int /*<<< orphan*/  RSLOBJ_TS_PGM ; 
 int _PGMCALL (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ) ; 
 int _RSLOBJ2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_ibmi_system_status(SSTS0200* rcvr) {
  /* rcvrlen is input parameter 2 to QWCRSSTS */
  unsigned int rcvrlen = sizeof(*rcvr);

  /* format is input parameter 3 to QWCRSSTS ("SSTS0200" in EBCDIC) */
  unsigned char format[] = {0xE2, 0xE2, 0xE3, 0xE2, 0xF0, 0xF2, 0xF0, 0xF0};

  /* reset_status is input parameter 4 to QWCRSSTS ("*NO       " in EBCDIC) */
  unsigned char reset_status[] = {
    0x5C, 0xD5, 0xD6, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40
  };

  /* errcode is input parameter 5 to QWCRSSTS */
  struct _errcode {
    int bytes_provided;
    int bytes_available;
    char msgid[7];
  } errcode;

  /* qwcrssts_pointer is the 16-byte tagged system pointer to QWCRSSTS */
  ILEpointer __attribute__((aligned(16))) qwcrssts_pointer;

  /* qwcrssts_argv is the array of argument pointers to QWCRSSTS */
  void* qwcrssts_argv[6];

  /* Set the IBM i pointer to the QSYS/QWCRSSTS *PGM object */
  int rc = _RSLOBJ2(&qwcrssts_pointer, RSLOBJ_TS_PGM, "QWCRSSTS", "QSYS");

  if (rc != 0)
    return rc;

  /* initialize the QWCRSSTS returned info structure */
  memset(rcvr, 0, sizeof(*rcvr));

  /* initialize the QWCRSSTS error code structure */
  memset(&errcode, 0, sizeof(errcode));
  errcode.bytes_provided = sizeof(errcode);

  /* initialize the array of argument pointers for the QWCRSSTS API */
  qwcrssts_argv[0] = rcvr;
  qwcrssts_argv[1] = &rcvrlen;
  qwcrssts_argv[2] = &format;
  qwcrssts_argv[3] = &reset_status;
  qwcrssts_argv[4] = &errcode;
  qwcrssts_argv[5] = NULL;

  /* Call the IBM i QWCRSSTS API from PASE */
  rc = _PGMCALL(&qwcrssts_pointer, (void**)&qwcrssts_argv, 0);

  return rc;
}