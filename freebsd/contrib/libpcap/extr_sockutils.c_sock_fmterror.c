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
typedef  int /*<<< orphan*/  message ;
typedef  char TCHAR ;

/* Variables and functions */
 int FORMAT_MESSAGE_FROM_SYSTEM ; 
 int FORMAT_MESSAGE_IGNORE_INSERTS ; 
 int FORMAT_MESSAGE_MAX_WIDTH_MASK ; 
 int FormatMessage (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SOCK_ERRBUF_SIZE ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int,char*,...) ; 
 char* strerror (int) ; 

void sock_fmterror(const char *caller, int errcode, char *errbuf, int errbuflen)
{
#ifdef _WIN32
	int retval;
	TCHAR message[SOCK_ERRBUF_SIZE];	/* It will be char (if we're using ascii) or wchar_t (if we're using unicode) */

	if (errbuf == NULL)
		return;

	retval = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
		FORMAT_MESSAGE_MAX_WIDTH_MASK,
		NULL, errcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		message, sizeof(message) / sizeof(TCHAR), NULL);

	if (retval == 0)
	{
		if ((caller) && (*caller))
			pcap_snprintf(errbuf, errbuflen, "%sUnable to get the exact error message", caller);
		else
			pcap_snprintf(errbuf, errbuflen, "Unable to get the exact error message");
	}
	else
	{
		if ((caller) && (*caller))
			pcap_snprintf(errbuf, errbuflen, "%s%s (code %d)", caller, message, errcode);
		else
			pcap_snprintf(errbuf, errbuflen, "%s (code %d)", message, errcode);
	}
#else
	char *message;

	if (errbuf == NULL)
		return;

	message = strerror(errcode);

	if ((caller) && (*caller))
		pcap_snprintf(errbuf, errbuflen, "%s%s (code %d)", caller, message, errcode);
	else
		pcap_snprintf(errbuf, errbuflen, "%s (code %d)", message, errcode);
#endif
}