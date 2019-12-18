int
mm_receive_fd(int sock)
{
#if defined(HAVE_RECVMSG) && (defined(HAVE_ACCRIGHTS_IN_MSGHDR) || defined(HAVE_CONTROL_IN_MSGHDR))
	struct msghdr msg;
#ifndef HAVE_ACCRIGHTS_IN_MSGHDR
	union {
		struct cmsghdr hdr;
		char buf[CMSG_SPACE(sizeof(int))];
	} cmsgbuf;
	struct cmsghdr *cmsg;
#endif
	struct iovec vec;
	ssize_t n;
	char ch;
	int fd;
	struct pollfd pfd;

	memset(&msg, 0, sizeof(msg));
	vec.iov_base = &ch;
	vec.iov_len = 1;
	msg.msg_iov = &vec;
	msg.msg_iovlen = 1;
#ifdef HAVE_ACCRIGHTS_IN_MSGHDR
	msg.msg_accrights = (caddr_t)&fd;
	msg.msg_accrightslen = sizeof(fd);
#else
	memset(&cmsgbuf, 0, sizeof(cmsgbuf));
	msg.msg_control = &cmsgbuf.buf;
	msg.msg_controllen = sizeof(cmsgbuf.buf);
#endif

	pfd.fd = sock;
	pfd.events = POLLIN;
	while ((n = recvmsg(sock, &msg, 0)) == -1 &&
	    (errno == EAGAIN || errno == EINTR)) {
		debug3("%s: recvmsg: %s", __func__, strerror(errno));
		(void)poll(&pfd, 1, -1);
	}
	if (n == -1) {
		error("%s: recvmsg: %s", __func__, strerror(errno));
		return -1;
	}

	if (n != 1) {
		error("%s: recvmsg: expected received 1 got %zd", __func__, n);
		return -1;
	}

#ifdef HAVE_ACCRIGHTS_IN_MSGHDR
	if (msg.msg_accrightslen != sizeof(fd)) {
		error("%s: no fd", __func__);
		return -1;
	}
#else
	cmsg = CMSG_FIRSTHDR(&msg);
	if (cmsg == NULL) {
		error("%s: no message header", __func__);
		return -1;
	}

#ifndef BROKEN_CMSG_TYPE
	if (cmsg->cmsg_type != SCM_RIGHTS) {
		error("%s: expected type %d got %d", __func__,
		    SCM_RIGHTS, cmsg->cmsg_type);
		return -1;
	}
#endif
	fd = (*(int *)CMSG_DATA(cmsg));
#endif
	return fd;
#else
	error("%s: file descriptor passing not supported", __func__);
	return -1;
#endif
}