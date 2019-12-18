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
typedef  unsigned char u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct tree_cache {int dummy; } ;
struct packet {TYPE_1__* options; } ;
struct dhcp_packet {unsigned char* options; unsigned char* file; unsigned char* sname; } ;
typedef  int /*<<< orphan*/  priority_list ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {unsigned char* data; int len; } ;

/* Variables and functions */
 size_t DHCP_FILE_LEN ; 
 int DHCP_FIXED_LEN ; 
 unsigned int DHCP_FIXED_NON_UDP ; 
 unsigned char* DHCP_OPTIONS_COOKIE ; 
 unsigned int DHCP_SNAME_LEN ; 
 unsigned char DHO_DHCP_LEASE_TIME ; 
 size_t DHO_DHCP_MAX_MESSAGE_SIZE ; 
 unsigned char DHO_DHCP_MESSAGE ; 
 unsigned char DHO_DHCP_MESSAGE_TYPE ; 
 unsigned char DHO_DHCP_OPTION_OVERLOAD ; 
 size_t DHO_DHCP_PARAMETER_REQUEST_LIST ; 
 unsigned char DHO_DHCP_SERVER_IDENTIFIER ; 
 unsigned char DHO_END ; 
 scalar_t__ DHO_PAD ; 
 unsigned char* dhcp_option_default_priority_list ; 
 int getUShort (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned int) ; 
 unsigned int sizeof_dhcp_option_default_priority_list ; 
 unsigned int store_options (unsigned char*,size_t,struct tree_cache**,unsigned char*,unsigned int,size_t,size_t,int) ; 

int
cons_options(struct packet *inpacket, struct dhcp_packet *outpacket,
    int mms, struct tree_cache **options,
    int overload, /* Overload flags that may be set. */
    int terminate, int bootpp, u_int8_t *prl, int prl_len)
{
	unsigned char priority_list[300], buffer[4096];
	unsigned priority_len;
	size_t main_buffer_size;
	unsigned option_size, bufix, mainbufix;
	int length;

	/*
	 * If the client has provided a maximum DHCP message size, use
	 * that; otherwise, if it's BOOTP, only 64 bytes; otherwise use
	 * up to the minimum IP MTU size (576 bytes).
	 *
	 * XXX if a BOOTP client specifies a max message size, we will
	 * honor it.
	 */
	if (!mms &&
	    inpacket &&
	    inpacket->options[DHO_DHCP_MAX_MESSAGE_SIZE].data &&
	    (inpacket->options[DHO_DHCP_MAX_MESSAGE_SIZE].len >=
	    sizeof(u_int16_t)))
		mms = getUShort(
		    inpacket->options[DHO_DHCP_MAX_MESSAGE_SIZE].data);

	if (mms)
		main_buffer_size = mms - DHCP_FIXED_LEN;
	else if (bootpp)
		main_buffer_size = 64;
	else
		main_buffer_size = 576 - DHCP_FIXED_LEN;

	if (main_buffer_size > sizeof(buffer))
		main_buffer_size = sizeof(buffer);

	/* Preload the option priority list with mandatory options. */
	priority_len = 0;
	priority_list[priority_len++] = DHO_DHCP_MESSAGE_TYPE;
	priority_list[priority_len++] = DHO_DHCP_SERVER_IDENTIFIER;
	priority_list[priority_len++] = DHO_DHCP_LEASE_TIME;
	priority_list[priority_len++] = DHO_DHCP_MESSAGE;

	/*
	 * If the client has provided a list of options that it wishes
	 * returned, use it to prioritize.  Otherwise, prioritize based
	 * on the default priority list.
	 */
	if (inpacket &&
	    inpacket->options[DHO_DHCP_PARAMETER_REQUEST_LIST].data) {
		unsigned prlen =
		    inpacket->options[DHO_DHCP_PARAMETER_REQUEST_LIST].len;
		if (prlen + priority_len > sizeof(priority_list))
			prlen = sizeof(priority_list) - priority_len;

		memcpy(&priority_list[priority_len],
		    inpacket->options[DHO_DHCP_PARAMETER_REQUEST_LIST].data,
		    prlen);
		priority_len += prlen;
		prl = priority_list;
	} else if (prl) {
		if (prl_len + priority_len > sizeof(priority_list))
			prl_len = sizeof(priority_list) - priority_len;

		memcpy(&priority_list[priority_len], prl, prl_len);
		priority_len += prl_len;
		prl = priority_list;
	} else {
		memcpy(&priority_list[priority_len],
		    dhcp_option_default_priority_list,
		    sizeof_dhcp_option_default_priority_list);
		priority_len += sizeof_dhcp_option_default_priority_list;
	}

	/* Copy the options into the big buffer... */
	option_size = store_options(
	    buffer,
	    (main_buffer_size - 7 + ((overload & 1) ? DHCP_FILE_LEN : 0) +
		((overload & 2) ? DHCP_SNAME_LEN : 0)),
	    options, priority_list, priority_len, main_buffer_size,
	    (main_buffer_size + ((overload & 1) ? DHCP_FILE_LEN : 0)),
	    terminate);

	/* Put the cookie up front... */
	memcpy(outpacket->options, DHCP_OPTIONS_COOKIE, 4);
	mainbufix = 4;

	/*
	 * If we're going to have to overload, store the overload option
	 * at the beginning.  If we can, though, just store the whole
	 * thing in the packet's option buffer and leave it at that.
	 */
	if (option_size <= main_buffer_size - mainbufix) {
		memcpy(&outpacket->options[mainbufix],
		    buffer, option_size);
		mainbufix += option_size;
		if (mainbufix < main_buffer_size)
			outpacket->options[mainbufix++] = DHO_END;
		length = DHCP_FIXED_NON_UDP + mainbufix;
	} else {
		outpacket->options[mainbufix++] = DHO_DHCP_OPTION_OVERLOAD;
		outpacket->options[mainbufix++] = 1;
		if (option_size >
		    main_buffer_size - mainbufix + DHCP_FILE_LEN)
			outpacket->options[mainbufix++] = 3;
		else
			outpacket->options[mainbufix++] = 1;

		memcpy(&outpacket->options[mainbufix],
		    buffer, main_buffer_size - mainbufix);
		bufix = main_buffer_size - mainbufix;
		length = DHCP_FIXED_NON_UDP + mainbufix;
		if (overload & 1) {
			if (option_size - bufix <= DHCP_FILE_LEN) {
				memcpy(outpacket->file,
				    &buffer[bufix], option_size - bufix);
				mainbufix = option_size - bufix;
				if (mainbufix < DHCP_FILE_LEN)
					outpacket->file[mainbufix++] = (char)DHO_END;
				while (mainbufix < DHCP_FILE_LEN)
					outpacket->file[mainbufix++] = (char)DHO_PAD;
			} else {
				memcpy(outpacket->file,
				    &buffer[bufix], DHCP_FILE_LEN);
				bufix += DHCP_FILE_LEN;
			}
		}
		if ((overload & 2) && option_size < bufix) {
			memcpy(outpacket->sname,
			    &buffer[bufix], option_size - bufix);

			mainbufix = option_size - bufix;
			if (mainbufix < DHCP_SNAME_LEN)
				outpacket->file[mainbufix++] = (char)DHO_END;
			while (mainbufix < DHCP_SNAME_LEN)
				outpacket->file[mainbufix++] = (char)DHO_PAD;
		}
	}
	return (length);
}