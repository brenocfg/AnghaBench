#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  TYPE_1__* xmlBufferPtr ;
struct TYPE_8__ {int /*<<< orphan*/  children; } ;
struct TYPE_7__ {int use; char* content; } ;

/* Variables and functions */
 int MAX_NETMESSAGE ; 
 int /*<<< orphan*/  NMSG_Clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NMSG_WriteString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Net_Send (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_NOXML ; 
 int /*<<< orphan*/  Sys_FPrintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ brdcst_socket ; 
 TYPE_3__* doc ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  msg ; 
 int /*<<< orphan*/  xmlAddChild (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xmlBufferCreate () ; 
 int /*<<< orphan*/  xmlBufferFree (TYPE_1__*) ; 
 int /*<<< orphan*/  xmlNodeDump (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xml_SendNode( xmlNodePtr node ){
	xmlBufferPtr xml_buf;
	char xmlbuf[MAX_NETMESSAGE]; // we have to copy content from the xmlBufferPtr into an aux buffer .. that sucks ..
	// this index loops through the node buffer
	int pos = 0;
	int size;

	xmlAddChild( doc->children, node );

	if ( brdcst_socket ) {
		xml_buf = xmlBufferCreate();
		xmlNodeDump( xml_buf, doc, node, 0, 0 );

		// the XML node might be too big to fit in a single network message
		// l_net library defines an upper limit of MAX_NETMESSAGE
		// there are some size check errors, so we use MAX_NETMESSAGE-10 to be safe
		// if the size of the buffer exceeds MAX_NETMESSAGE-10 we'll send in several network messages
		while ( pos < xml_buf->use )
		{
			// what size are we gonna send now?
			( xml_buf->use - pos < MAX_NETMESSAGE - 10 ) ? ( size = xml_buf->use - pos ) : ( size = MAX_NETMESSAGE - 10 );
			//++timo just a debug thing
			if ( size == MAX_NETMESSAGE - 10 ) {
				Sys_FPrintf( SYS_NOXML, "Got to split the buffer\n" );
			}
			memcpy( xmlbuf, xml_buf->content + pos, size );
			xmlbuf[size] = '\0';
			NMSG_Clear( &msg );
			NMSG_WriteString( &msg, xmlbuf );
			Net_Send( brdcst_socket, &msg );
			// now that the thing is sent prepare to loop again
			pos += size;
		}

#if 0
		// NOTE: the NMSG_WriteString is limited to MAX_NETMESSAGE
		// we will need to split into chunks
		// (we could also go lower level, in the end it's using send and receiv which are not size limited)
		//++timo FIXME: MAX_NETMESSAGE is not exactly the max size we can stick in the message
		//  there's some tweaking to do in l_net for that .. so let's give us a margin for now

		//++timo we need to handle the case of a buffer too big to fit in a single message
		// try without checks for now
		if ( xml_buf->use > MAX_NETMESSAGE - 10 ) {
			// if we send that we are probably gonna break the stream at the other end..
			// and Error will call right there
			//Error( "MAX_NETMESSAGE exceeded for XML feedback stream in FPrintf (%d)\n", xml_buf->use);
			Sys_FPrintf( SYS_NOXML, "MAX_NETMESSAGE exceeded for XML feedback stream in FPrintf (%d)\n", xml_buf->use );
			xml_buf->content[xml_buf->use] = '\0'; //++timo this corrupts the buffer but we don't care it's for printing
			Sys_FPrintf( SYS_NOXML, xml_buf->content );

		}

		size = xml_buf->use;
		memcpy( xmlbuf, xml_buf->content, size );
		xmlbuf[size] = '\0';
		NMSG_Clear( &msg );
		NMSG_WriteString( &msg, xmlbuf );
		Net_Send( brdcst_socket, &msg );
#endif

		xmlBufferFree( xml_buf );
	}
}