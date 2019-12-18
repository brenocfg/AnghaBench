int
mm_send_fd(int sock, int fd)
{
#if defined(HAVE_SENDMSG) && (defined(HAVE_ACCRIGHTS_IN_MSGHDR) || defined(HAVE_CONTROL_IN_MSGHDR))
	struct msghdr msg;
#ifndef HAVE_ACCRIGHTS_IN_MSGHDR
	union {
		struct cmsghdr hdr;
		char buf[CMSG_SPACE(sizeof(int))];
	} cmsgbuf;
	struct cmsghdr *cmsg;
#endif
	struct iovec vec;
	char ch = '\0';
	ssize_t n;
	struct pollfd pfd;

	memset(&msg, 0, sizeof(msg));
#ifdef HAVE_ACCRIGHTS_IN_MSGHDR
	msg.msg_accrights = (caddr_t)&fd;
	msg.msg_accrightslen = sizeof(fd);
#else
	memset(&cmsgbuf, 0, sizeof(cmsgbuf));
	msg.msg_control = (caddr_t)&cmsgbuf.buf;
	msg.msg_controllen = sizeof(cmsgbuf.buf);
	cmsg = CMSG_FIRSTHDR(&msg);
	cmsg->cmsg_len = CMSG_LEN(sizeof(int));
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	*(int *)CMSG_DATA(cmsg) = fd;
#endif

	vec.iov_base = &ch;
	vec.iov_len = 1;
	msg.msg_iov = &vec;
	msg.msg_iovlen = 1;

	pfd.fd = sock;
	pfd.events = POLLOUT;
	while ((n = sendmsg(sock, &msg, 0)) == -1 &&
	    (errno == EAGAIN || errno == EINTR)) {
		debug3("%s: sendmsg(%d): %s", __func__, fd, strerror(errno));
		(void)poll(&pfd, 1, -1);
	}
	if (n == -1) {
		error("%s: sendmsg(%d): %s", __func__, fd,
		    strerror(errno));
		return -1;
	}

	if (n != 1) {
		error("%s: sendmsg: expected sent 1 got %zd", __func__, n);
		return -1;
	}
	return 0;
#else
	error("%s: file descriptor passing not supported", __func__);
	return -1;
#endif
}