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
typedef  int apr_status_t ;

/* Variables and functions */
#define  SERF_ERROR_ABORTED_CONNECTION 141 
#define  SERF_ERROR_AUTHN_FAILED 140 
#define  SERF_ERROR_AUTHN_INITALIZATION_FAILED 139 
#define  SERF_ERROR_AUTHN_MISSING_ATTRIBUTE 138 
#define  SERF_ERROR_AUTHN_NOT_SUPPORTED 137 
#define  SERF_ERROR_BAD_HTTP_RESPONSE 136 
#define  SERF_ERROR_CLOSING 135 
#define  SERF_ERROR_DECOMPRESSION_FAILED 134 
#define  SERF_ERROR_REQUEST_LOST 133 
#define  SERF_ERROR_SSLTUNNEL_SETUP_FAILED 132 
#define  SERF_ERROR_SSL_CERT_FAILED 131 
#define  SERF_ERROR_SSL_COMM_FAILED 130 
#define  SERF_ERROR_TRUNCATED_HTTP_RESPONSE 129 
#define  SERF_ERROR_WAIT_CONN 128 

const char *serf_error_string(apr_status_t errcode)
{
    switch (errcode)
    {
    case SERF_ERROR_CLOSING:
        return "The connection is closing";
    case SERF_ERROR_REQUEST_LOST:
        return "A request has been lost";
    case SERF_ERROR_WAIT_CONN:
        return "The connection is blocked, pending further action";
    case SERF_ERROR_DECOMPRESSION_FAILED:
        return "An error occurred during decompression";
    case SERF_ERROR_BAD_HTTP_RESPONSE:
        return "The server sent an improper HTTP response";
    case SERF_ERROR_TRUNCATED_HTTP_RESPONSE:
        return "The server sent a truncated HTTP response body.";
    case SERF_ERROR_ABORTED_CONNECTION:
        return "The server unexpectedly closed the connection.";
    case SERF_ERROR_SSL_COMM_FAILED:
        return "An error occurred during SSL communication";
    case SERF_ERROR_SSL_CERT_FAILED:
        return "An SSL certificate related error occurred ";
    case SERF_ERROR_AUTHN_FAILED:
        return "An error occurred during authentication";
    case SERF_ERROR_AUTHN_NOT_SUPPORTED:
        return "The requested authentication type(s) are not supported";
    case SERF_ERROR_AUTHN_MISSING_ATTRIBUTE:
        return "An authentication attribute is missing";
    case SERF_ERROR_AUTHN_INITALIZATION_FAILED:
        return "Initialization of an authentication type failed";
    case SERF_ERROR_SSLTUNNEL_SETUP_FAILED:
        return "The proxy server returned an error while setting up the "
               "SSL tunnel.";
    default:
        return NULL;
    }

    /* NOTREACHED  */
}